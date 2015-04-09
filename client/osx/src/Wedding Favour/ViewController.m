//
//  ViewController.m
//  Wedding Favour
//
//  Created by Mike T on 05/04/2015.
//  Copyright (c) 2015 Stephen and Amy Bridges. All rights reserved.
//

#import "ViewController.h"
#import "AppDelegate.h"
#import <IOKit/hid/IOHIDLib.h>
#import <IOKit/usb/IOUSBLib.h>
#import <Carbon/Carbon.h>

@implementation ViewController

//Global variables
static IOHIDElementCookie capslock_cookie = (IOHIDElementCookie)0;
static IONotificationPortRef    gNotifyPort;
static io_iterator_t            gRawAddedIter;
static io_iterator_t            gRawRemovedIter;
static EventHotKeyRef           gCarbonHotKey;

#ifdef DEBUG
#define LOG(format, ...) printf(format, __VA_ARGS__);
#else
#define LOG(format,  ...)
#endif

// Actual Favour
#define FAVOUR_VID (0x03eb)
#define FAVOUR_PID (0x2042)

// Load function to set up the view
- (void)viewDidLoad {
    [super viewDidLoad];

    // Disable the button until we see a device
    NSButton *button0 = [self.view viewWithTag:0];
    [button0 setEnabled:NO];
    
    // Register the hotkey and notifications
    [self RegisterHotKey];
    [self RegisterDeviceNotifications];
    
}

// Clean up some of the notifications on exit
- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:@"HotKeyEvent"
                                                  object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:@"InsertionEvent"
                                                  object:nil];
    if (gCarbonHotKey)
    {
        UnregisterEventHotKey(gCarbonHotKey);
    }
}


// Registers a global hotkey to trigger the toggle
- (void) RegisterHotKey{
    EventTypeSpec eventType;
    eventType.eventClass=kEventClassKeyboard;
    eventType.eventKind=kEventHotKeyPressed;
    
    // Need to install a main application handler
    InstallApplicationEventHandler(&HotKeyHandler,1,&eventType,NULL,NULL);

    // Create the event and ID
    EventHotKeyID keyID;
    keyID.signature = 'htk1';
    keyID.id = 0;

    // Register the event.
    // 0x0D = w
    OSStatus err = RegisterEventHotKey(0x0D, controlKey+optionKey, keyID, GetEventDispatcherTarget(), 0, &gCarbonHotKey);
    
    if (err)
    {
        LOG("%s", GetMacOSStatusErrorString(err));
    }
    
    // Need to create a notification so that we can send the view controller a message from the key callback.
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onTheEvent)
                                                 name:@"HotKeyEvent"
                                               object:nil];

}

// View Controller notification handler for the key press
- (void)onTheEvent{
    [self ToggleState];
}

// Eventhandler for the key press.
OSStatus HotKeyHandler(EventHandlerCallRef nextHandler,EventRef theEvent,
                         void *userData)
{
    // Fire a notification to the View Controller
    [[NSNotificationCenter defaultCenter] postNotificationName:@"HotKeyEvent" object:nil];
    return noErr;
}

// Generic Toggle handler
- (void)ToggleState{
    NSButton *button0 = [self.view viewWithTag:0];
    if ([button0 isEnabled])
    {
        // Just do a low-high-low transition
        manipulate_led(1);
        manipulate_led(0);
    }
}

// Button click handler
- (IBAction)buttonOnCLick:(id)sender {
    [self ToggleState];
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];
}

// Sets up this application to register for device intertion events
- (void) RegisterDeviceNotifications{
    
    mach_port_t             masterPort;
    CFMutableDictionaryRef  matchingDict;
    CFRunLoopSourceRef      runLoopSource;
    kern_return_t           kr;
    SInt32                  usbVendor = FAVOUR_VID;
    SInt32                  usbProduct = FAVOUR_PID;
    
    do
    {
        
        // Need to create a notification so that we can send the view controller a message form the key callback.
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onInsertionEvent:)
                                                     name:@"InsertionEvent"
                                                   object:nil];
        
        //Create a master port for communication with the I/O Kit
        kr = IOMasterPort(MACH_PORT_NULL, &masterPort);
        if (kr || !masterPort)
        {
            printf("ERR: Couldn’t create a master I/O Kit port(%08x)\n", kr);
            break;
        }
        //Set up matching dictionary for class IOUSBDevice and its subclasses
        matchingDict = IOServiceMatching(kIOUSBDeviceClassName);
        if (!matchingDict)
        {
            printf("Couldn’t create a USB matching dictionary\n");
            mach_port_deallocate(mach_task_self(), masterPort);
            break;
        }
        
        //Add the vendor and product IDs to the matching dictionary.
        //This is the second key in the table of device-matching keys of the
        //USB Common Class Specification
        CFDictionarySetValue(matchingDict, CFSTR(kUSBVendorID),
                             CFNumberCreate(kCFAllocatorDefault,
                                            kCFNumberSInt32Type, &usbVendor));
        CFDictionarySetValue(matchingDict, CFSTR(kUSBProductID),
                             CFNumberCreate(kCFAllocatorDefault,
                                            kCFNumberSInt32Type, &usbProduct));
        
        //To set up asynchronous notifications, create a notification port and
        //add its run loop event source to the program’s run loop
        gNotifyPort = IONotificationPortCreate(masterPort);
        runLoopSource = IONotificationPortGetRunLoopSource(gNotifyPort);
        CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource,
                           kCFRunLoopDefaultMode);
        
        //Retain additional dictionary references because each call to
        //IOServiceAddMatchingNotification consumes one reference
        matchingDict = (CFMutableDictionaryRef) CFRetain(matchingDict);
        matchingDict = (CFMutableDictionaryRef) CFRetain(matchingDict);
        matchingDict = (CFMutableDictionaryRef) CFRetain(matchingDict);
        
        //Now set up two notifications: one to be called when a raw device
        //is first matched by the I/O Kit and another to be called when the
        //device is terminated
        //Notification of first match:
        kr = IOServiceAddMatchingNotification(gNotifyPort,
                                              kIOFirstMatchNotification, matchingDict,
                                              RawDeviceAdded, NULL, &gRawAddedIter);
        //Iterate over set of matching devices to access already-present devices
        //and to arm the notification
        RawDeviceAdded(NULL, gRawAddedIter);
        
        //Notification of termination:
        kr = IOServiceAddMatchingNotification(gNotifyPort,
                                              kIOTerminatedNotification, matchingDict,
                                              RawDeviceRemoved, NULL, &gRawRemovedIter);
        // Arm the removal handler
        RawDeviceRemoved(NULL, gRawRemovedIter);
        
        //Finished with master port
        mach_port_deallocate(mach_task_self(), masterPort);
        masterPort = 0;
        
    }while(0);
}

// Handler for processing insertion event inside the view
- (void)onInsertionEvent:(NSNotification *)n {
    NSButton *button0 = [self.view viewWithTag:0];
    
    if ([n.userInfo[@"inserted"]boolValue])
    {
        [button0 setEnabled: YES];
        int value = 0;
        if (getLEDValue(&value))
        {
            // Make sure the LED is OFF
            manipulate_led(0);
        }
    }
    else
    {
        [button0 setEnabled: NO];
    }
    
}

// Callback for the device insertion
void RawDeviceAdded(void *refCon, io_iterator_t iterator)
{
    io_service_t                usbDevice;
    // Just loop round the iterator
    while ((usbDevice = IOIteratorNext(iterator)))
    {
        NSDictionary * userInfo = @{ @"inserted" : @true};
        [[NSNotificationCenter defaultCenter] postNotificationName:@"InsertionEvent" object:nil userInfo:userInfo];
        IOObjectRelease(usbDevice);
    }
    
}

// Callback for the device removal
void RawDeviceRemoved(void *refCon, io_iterator_t iterator)
{
    io_service_t                usbDevice;
    // Just loop round the iterator
    while ((usbDevice = IOIteratorNext(iterator)))
    {
        NSDictionary * userInfo = @{ @"inserted" : @false};
        [[NSNotificationCenter defaultCenter] postNotificationName:@"InsertionEvent" object:nil userInfo:userInfo];
        IOObjectRelease(usbDevice);
    };
    
}

// Finds our keyboard device from the HID service
io_service_t find_a_keyboard(void)
{
    io_service_t result = (io_service_t)0;
    
    CFNumberRef vidRef = (CFNumberRef)0;
    CFNumberRef pidRef = (CFNumberRef)0;
    CFMutableDictionaryRef matchingDictRef = (CFMutableDictionaryRef)0;
    
    if (!(matchingDictRef = IOServiceMatching(kIOHIDDeviceKey))) {
        return result;
    }
    
    UInt32 vid = FAVOUR_VID;
    UInt32 pid = FAVOUR_PID;
    
    
    if ((vidRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &vid)))
    {
        if ((pidRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType,&pid)))
        {
            CFDictionarySetValue(matchingDictRef, CFSTR(kIOHIDVendorIDKey),
                                 vidRef);
            CFDictionarySetValue(matchingDictRef, CFSTR(kIOHIDProductIDKey),
                                 pidRef);
        
        result = IOServiceGetMatchingService(kIOMasterPortDefault, matchingDictRef);
        }
    }
    
    if (vidRef)
    {
        CFRelease(vidRef);
    }
    if (pidRef)
    {
        CFRelease(pidRef);
    }
    
    return result;
}

// Gets the LED cookies from the HID device
void find_led_cookies(IOHIDDeviceInterface122** handle)
{
    IOHIDElementCookie cookie;
    CFTypeRef          object;
    long               number;
    long               usage;
    long               usagePage;
    CFArrayRef         elements;
    CFDictionaryRef    element;
    IOReturn           result;
    
    if (!handle || !(*handle)) {
        return;
    }
    
    result = (*handle)->copyMatchingElements(handle, NULL, &elements);
    
    if (result != kIOReturnSuccess)
    {
        LOG("%s", "Failed to copy cookies.\n");
        return;
    }
    
    CFIndex i;
    
    for (i = 0; i < CFArrayGetCount(elements); i++)
    {
        
        element = CFArrayGetValueAtIndex(elements, i);
        
        object = (CFDictionaryGetValue(element, CFSTR(kIOHIDElementCookieKey)));
        if (object == 0 || CFGetTypeID(object) != CFNumberGetTypeID())
        {
            continue;
        }
        if (!CFNumberGetValue((CFNumberRef) object, kCFNumberLongType,
                              &number))
        {
            continue;
        }
        cookie = (IOHIDElementCookie)number;
        
        object = CFDictionaryGetValue(element, CFSTR(kIOHIDElementUsageKey));
        if (object == 0 || CFGetTypeID(object) != CFNumberGetTypeID())
        {
            continue;
        }
        if (!CFNumberGetValue((CFNumberRef)object, kCFNumberLongType,
                              &number))
        {
            continue;
        }
        usage = number;
        
        object = CFDictionaryGetValue(element,CFSTR(kIOHIDElementUsagePageKey));
        if (object == 0 || CFGetTypeID(object) != CFNumberGetTypeID())
        {
            continue;
        }
        if (!CFNumberGetValue((CFNumberRef)object, kCFNumberLongType,
                              &number))
        {
            continue;
        }
        usagePage = number;
        
        if (usagePage == kHIDPage_LEDs)
        {
            if (usage == kHIDUsage_LED_CapsLock)
            {
                capslock_cookie = cookie;
            }
        }
    }
    
    return;
}

// Creates a HID interface for manipulation
void create_hid_interface(io_object_t hidDevice, IOHIDDeviceInterface*** hdi)
{
    IOCFPlugInInterface** plugInInterface = NULL;
    
    io_name_t className;
    HRESULT   plugInResult = S_OK;
    SInt32    score = 0;
    IOReturn  ioReturnValue = kIOReturnSuccess;
    
    ioReturnValue = IOObjectGetClass(hidDevice, className);
    
    if (ioReturnValue != kIOReturnSuccess)
    {
        NSAlert *alert = [[NSAlert alloc] init];
        [alert setMessageText:@"Failed to get class name."];
        [alert runModal];
    }
    
    ioReturnValue = IOCreatePlugInInterfaceForService(
                                                      hidDevice, kIOHIDDeviceUserClientTypeID,
                                                      kIOCFPlugInInterfaceID, &plugInInterface, &score);
    if (ioReturnValue != kIOReturnSuccess) {
        return;
    }
    
    plugInResult = (*plugInInterface)->QueryInterface(plugInInterface,
                                                      CFUUIDGetUUIDBytes(kIOHIDDeviceInterfaceID), (LPVOID)hdi);
    
    if (ioReturnValue != kIOReturnSuccess)
    {
        NSAlert *alert = [[NSAlert alloc] init];
        [alert setMessageText:@"Failed to create device interface."];
        [alert runModal];
    }
    
    (*plugInInterface)->Release(plugInInterface);
}

// Gets the LED value from the keyboard
int getLEDValue(int* value)
{
    io_service_t           hidService = (io_service_t)0;
    io_object_t            hidDevice = (io_object_t)0;
    IOHIDDeviceInterface **hidDeviceInterface = NULL;
    IOReturn               ioReturnValue = kIOReturnError;
    IOHIDEventStruct       theEvent;
    Boolean                result = false;
    
    if (!(hidService = find_a_keyboard()))
    {
        LOG("%s", "No keyboard found.\n");
        return ioReturnValue;
    }
    
    hidDevice = (io_object_t)hidService;
    
    create_hid_interface(hidDevice, &hidDeviceInterface);
    
    find_led_cookies((IOHIDDeviceInterface122 **)hidDeviceInterface);
    
    do
    {
        ioReturnValue = IOObjectRelease(hidDevice);
        if (ioReturnValue != kIOReturnSuccess)
        {
            break;
        }
        
        ioReturnValue = kIOReturnError;
        
        if (hidDeviceInterface == NULL)
        {
            LOG("%s", "Failed to create HID device interface.\n");
            return ioReturnValue;
        }
        
        if (capslock_cookie == 0) {
            LOG("%s", "Bad or missing LED cookie.\n");
            break;
        }
        
        ioReturnValue = (*hidDeviceInterface)->open(hidDeviceInterface, 0);
        if (ioReturnValue != kIOReturnSuccess) {
            LOG("%s", "Failed to open HID device interface.\n");
            break;
        }
        
        ioReturnValue = (*hidDeviceInterface)->getElementValue(hidDeviceInterface,
                                                               capslock_cookie, &theEvent);
        if (ioReturnValue != kIOReturnSuccess) {
            (void)(*hidDeviceInterface)->close(hidDeviceInterface);
            break;
        }
        else
        {   *value = theEvent.value;
            result = true;
        }
    }while(0);
    
    return result;
}

int
manipulate_led(UInt32 value)
{
    io_service_t           hidService = (io_service_t)0;
    io_object_t            hidDevice = (io_object_t)0;
    IOHIDDeviceInterface **hidDeviceInterface = NULL;
    IOReturn               ioReturnValue = kIOReturnError;
    IOHIDEventStruct       theEvent;
    
    if (!(hidService = find_a_keyboard())) {
        LOG("%s", "No keyboard found.\n");
        return ioReturnValue;
    }
    
    hidDevice = (io_object_t)hidService;
    
    create_hid_interface(hidDevice, &hidDeviceInterface);
    
    find_led_cookies((IOHIDDeviceInterface122 **)hidDeviceInterface);
    
    ioReturnValue = IOObjectRelease(hidDevice);
    if (ioReturnValue != kIOReturnSuccess)
    {
        if (*hidDeviceInterface)
        {
            (void)(*hidDeviceInterface)->Release(hidDeviceInterface);
        }
        return ioReturnValue;
    }
    
    ioReturnValue = kIOReturnError;
    
    if (hidDeviceInterface == NULL)
    {
        LOG("%s", "Failed to create HID device interface.\n");
        return ioReturnValue;
    }
    
    if (capslock_cookie == 0)
    {
        LOG("%s", "Bad or missing LED cookie.\n");

    }
    else
    {
        ioReturnValue = (*hidDeviceInterface)->open(hidDeviceInterface, 0);
        if (ioReturnValue != kIOReturnSuccess)
        {
            LOG("%s", "Failed to open HID device interface.\n");
        }
        else
        {
            ioReturnValue = (*hidDeviceInterface)->getElementValue(hidDeviceInterface,
                                                                   capslock_cookie, &theEvent);
            if (ioReturnValue != kIOReturnSuccess)
            {
                (void)(*hidDeviceInterface)->close(hidDeviceInterface);
            }
            else
            {
                LOG("%s\n", (theEvent.value) ? "on" : "off");
                if (value != -1)
                {
                    // Need to change the value
                    if (theEvent.value != value)
                    {
                        theEvent.value = value;
                        ioReturnValue = (*hidDeviceInterface)->setElementValue(hidDeviceInterface, capslock_cookie,
                                                                               &theEvent, 0, 0, 0, 0);
                        if (ioReturnValue == kIOReturnSuccess)
                        {
                            LOG("%s\n", (theEvent.value) ? "on" : "off");
                        }
                    }
                }
            }
            ioReturnValue = (*hidDeviceInterface)->close(hidDeviceInterface);
        }
    }
    
    (void)(*hidDeviceInterface)->Release(hidDeviceInterface);
    
    return ioReturnValue;
}


@end
