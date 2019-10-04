# iOS-MAS-Proximity

MASProximity is the core proximity framework of the iOS Mobile SDK, which is part of CA Mobile API Gateway. It gives developers the ability to process authentication and authorization through Bluetooth capability of iOS/Android devices, and QR Code.

## Features

The MASProximity framework comes with the following features:

- Authenticate or authorize through iOS and Android devices' built-in Bluetooth feature
- Authenticate or authorize through QR Code

## Get Started

- Check out our [documentation][docs] for sample code, video tutorials, and more.
- [Download MASProximity][download] 

## Communication

- *Have general questions or need help?*, use [Stack Overflow][StackOverflow]. (Tag 'massdk')
- *Find a bug?*, open an issue with the steps to reproduce it.
- *Request a feature or have an idea?*, open an issue.

## How You Can Contribute

Contributions are welcome and much appreciated. To learn more, see the [Contribution Guidelines][contributing].

## Installation

MASProximity supports multiple methods for installing the library in a project.

### Cocoapods (Podfile) Install

To integrate MASProximity into your Xcode project using CocoaPods, specify it in your **Podfile:**

```
source 'https://github.com/CocoaPods/Specs.git'
platform :ios, '9.0'

pod 'MASProximity'
```
Then, run the following command using the command prompt from the folder of your project:

```
$ pod install
```

### Manual Install

For manual install, you add the Mobile SDK to your Xcode project. Note that you must add the MASFoundation library. For complete MAS functionality, install all of the MAS libraries as shown.

1. Open your project in Xcode.
2. Drag the SDK library files, and drop them into your project in the left navigator panel in Xcode. Select the option, `Copy items if needed`.
3. Select `File->Add files to 'project name'` and add the msso_config.json file from your project folder.
4. In Xcode "Build Setting” of your Project Target, add `-ObjC` for `Other Linker Flags`.
5. Import the following Mobile SDK library header file to the classes or to the .pch file if your project has one.

```
#import <MASFoundation/MASFoundation.h>
#import <MASProximity/MASProximity.h>
```

## Usage

After MASProximity is added to a project, `MASDevice` object from the MASFoundation library automatically displays proximity login methods. This saves you development time and makes the code cleaner. You write just a few lines of code, and the library automatically handles all of the settings for authenticating, and authorizing the session between devices.

When a user wants to login, there are various ways of authenticating the user's session using MAG SDK:

- Resource Owner Password Credentials Grant
- Social Login 
- Proximity Login (BLE, and QR Code)

Following sample codes will guide you through how to implement Proximity Login using MASProximity library.

### QR Code

#### Authenticating Session through QR Code

When the user wants to login through QR Code, simply display QR Code image generated by MASProximity library, and authenticate the user using received authorization code through `MASProximityLoginQRCode`.

```Objective-c

// Retrieve MASAuthenticationProvider for qrCode
MASAuthenticationProvider *proximity = nil;

for (MASAuthenticationProvider *provider in [MASAuthenticationProviders currentProviders])
{
	if (provider.isQrCode)
	{
		proximity = provider;
	}
}

// Construct MASProximityLoginQRCode using MASAuthenticationProvider
MASProximityLoginQRCode *qrCode = [[MASProximityLoginQRCode alloc] initWithAuthenticationProvider: proximity];

// Retreive UIImage of QR Code, and display it on your User Interface for other devices to scane the QR Code.
UIImage *qrCodeImg = [qrCode startDisplayingQRCodeImageForProximityLogin];

// At any time, if you wish to stop showing the QR Code, or authentication was done through other method, stop displaying the QR Code 
[qrCode stopDisplayingQRCodeImageForProximityLogin];
```

Another part that you should do is to handle the incoming authorizing code from QR Code authentication, or handle any error case that may happen during this process. You can handle this success or failure cases by using either of `NSNotification` base handling, or `MASProximityLoginDelegate`

##### Receiving Authorization Code or Error using NSNotification

There are few notification keys that will notify you during this process.  

- `MASProximityLoginQRCodeDidStartDisplayingQRCodeImage`: Notifies when QR Code image starts displaying and polling from the server
- `MASProximityLoginQRCodeDidStopDisplayingQRCodeImage`: Notifies when QR Code image stops displaying and polling from the server
- `MASDeviceDidReceiveAuthorizationCodeFromProximityLoginNotification`: Notifies when authorization code is received from the server through QR Code
- `MASDeviceDidReceiveErrorFromProximityLoginNotification`: Notifies when QR Code authorization fails anytime during the process


```
// Register notification for successful authorization
[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceiveAuthorizationCodeFromSessionSharing:) name:MASDeviceDidReceiveAuthorizationCodeFromProximityLoginNotification object:nil];
    
- (void)didReceiveAuthorizationCodeFromSessionSharing:(NSNotification *)notification
{
    NSString *authorizationCode = [notification.object objectForKey:@"code"];
	
	// Use the authorization code received from the notification to authenticate the user
	[MASUser loginWithAuthorizationCode:authorizationCode completion:^(BOOL completed, NSError *error) {
	
		// handle success or failure case here
	}];    
}

// Register notification for failure in authorization
[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceiveErrorFromSessionSharing:) name: MASDeviceDidReceiveErrorFromProximityLoginNotification object:nil];
    
- (void)didReceiveErrorFromSessionSharing:(NSNotification *)notification
{
	NSError *error = (NSError *)notification.object;
	
	// handle the error
}
```

##### Receiving Authorization Code or Error using MASProximityLoginDelegate


```
// Set delegation for handling Proximity Login
[MASDevice setProximityLoginDelegate:self];
	
// Implement authorization code response
- (void)didReceiveAuthorizationCode:(NSString *_Nonnull)authorizationCode
{
	// Use the authorization code received from the notification to authenticate the user
	[MASUser loginWithAuthorizationCode:authorizationCode completion:^(BOOL completed, NSError *error) {
	
		// handle success or failure case here
	}];   
} 

// Implement authorization failure response
- (void)didReceiveProximityLoginError:(NSError *_Nonnull)error
{
	NSError *error = (NSError *)notification.object;
	
	// handle the error
}
```

#### Authorizing Session through QR Code

When a device wants to authorize another device to grant or transfer authenticated session, you will need to implement image capture screen using `AVCaptureSession` to capture QR Code data. Once the application captures the QR Code data, you can simply validate it against `MASProximityLoginQRCode`

**Note** that you can only authorize other devices when you have a valid authenticated session on the device.

```
//	Retreive QR Code data using AVCaptureSession
NSString *qrCode = @"your data of QR Code";

[MASProximityLoginQRCode authorizeAuthenticateUrl:qrCode completion:^(BOOL completed, NSError *error) {

	if (error)
	{
		// handle error case
	}
	else {
		// authorization successful
	}
}];
```

Once the authorization is successfully done, authenticating device will automatically be able to poll authorization code on its device, and should be able to proceed authentication process.

### BLE

For BLE Proximity Login, there are two components involved in this process just like in QR Code:

- Authorizing Device (using Bluetooth Peripheral)
- Authenticating Device (using Bluetooth Central)

#### Authorizing Session through QR Code

When authorizing the session through BLE, the device must be authenticated prior to authorize other devices.

To authorize other devices through BLE, you will need to implement mandatory `MASProximityLoginDelegate` protocol method `[MASProximityLoginDelegate handleBLEProximityLoginUserConsent:deviceName:]`.

```
// Set delegation for handling Proximity Login
[MASDevice setProximityLoginDelegate:self];

// Start Bluetooth peripheral to observe other devices seeking for authorization
[[MASDevice currentDevice] startAsBluetoothPeripheral];

// Stop Bluetooth peripheral to stop observing other devices seeking for authorization
[[MASDevice currentDevice] stopAsBluetoothPeripheral];

// Implement the MASProximityLoginDelegate protocol to ask user's consent to authorize other device(s).
- (void)handleBLEProximityLoginUserConsent:(MASCompletionErrorBlock)completion deviceName:(NSString *)deviceName
{
	// Ask user's consent to authorize other devices using UIAlertController or other methods with given information.
	
	// If user does not want to authorize other device, simply call following
	completion(NO, nil);
	
	// If user allows to authorize other device, simply call following
	completion(YES, nil);
}
```

#### Authenticating Session through QR Code

When authenticating the session through BLE, you will simply need to call `MASDevice`'s proximity method and handle the response.

```
// Simply start scanning other devices to authorize the session
[[MASDevice currentDevice] startAsBluetoothCentral];

// Stop scanning other devices
[[MASDevice currentDevice] stopAsBluetoothCentral];
```

##### Handling Result of BLE Central

Once authenticating device and authorizing device finish their communication, the result of Proximity Login will be notified to the app through `NSNotification` or `MASProximityLoginDelegate`.

##### Receiving Authorization Code or Error using NSNotification

There are few notification keys that will notify you during this process.  

- `MASDeviceDidReceiveAuthorizationCodeFromProximityLoginNotification`: Notifies when authorization code is received from the server through BLE
- `MASDeviceDidReceiveErrorFromProximityLoginNotification`: Notifies when BLE authorization/authentication fails anytime during the process


```
// Register notification for successful authorization
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceiveAuthorizationCodeFromSessionSharing:) name:MASDeviceDidReceiveAuthorizationCodeFromProximityLoginNotification object:nil];
    
- (void)didReceiveAuthorizationCodeFromSessionSharing:(NSNotification *)notification
{
    NSString *authorizationCode = [notification.object objectForKey:@"code"];
	
	// Use the authorization code received from the notification to authenticate the user
	[MASUser loginWithAuthorizationCode:authorizationCode completion:^(BOOL completed, NSError *error) {
	
		// handle success or failure case here
	}];    
}

// Register notification for failure in authorization
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceiveErrorFromSessionSharing:) name: MASDeviceDidReceiveErrorFromProximityLoginNotification object:nil];
    
- (void)didReceiveErrorFromSessionSharing:(NSNotification *)notification
{
	NSError *error = (NSError *)notification.object;
	
	// handle the error
}
```

##### Receiving Authorization Code or Error using MASProximityLoginDelegate

```
// Set delegation for handling Proximity Login
[MASDevice setProximityLoginDelegate:self];
	
// Implement authorization code response
- (void)didReceiveAuthorizationCode:(NSString *_Nonnull)authorizationCode
{
	// Use the authorization code received from the notification to authenticate the user
	[MASUser loginWithAuthorizationCode:authorizationCode completion:^(BOOL completed, NSError *error) {
	
		// handle success or failure case here
	}];   
} 

// Implement authorization failure response
- (void)didReceiveProximityLoginError:(NSError *_Nonnull)error
{
	NSError *error = (NSError *)notification.object;
	
	// handle the error
}
```

##### Monitoring BLE State

For both authorizing and authenticating devices, you can monitor each state of BLE transaction through `MASProximityLoginDelegate` with `MASBLEServiceState`.

```
// Set delegation for handling Proximity Login
[MASDevice setProximityLoginDelegate:self];

// Implement optional BLE state for authorization/authentication process
- (void)didReceiveBLEProximityLoginStateUpdate:(MASBLEServiceState)state
{
	// monitor the state
}

```

## License

Copyright (c) 2019 Broadcom. All Rights Reserved.
The term "Broadcom" refers to Broadcom Inc. and/or its subsidiaries.

This software may be modified and distributed under the terms
of the MIT license. See the [LICENSE][license-link] file for details.


 [techdocs.broadcom.com]: http://techdocs.broadcom.com/content/broadcom/techdocs/us/en/ca-enterprise-software/layer7-api-management/mobile-sdk-for-ca-mobile-api-gateway/2-0.html
 [get-started]: http://techdocs.broadcom.com/content/broadcom/techdocs/us/en/ca-enterprise-software/layer7-api-management/mobile-sdk-for-ca-mobile-api-gateway/2-0.html
 [docs]: http://techdocs.broadcom.com/content/broadcom/techdocs/us/en/ca-enterprise-software/layer7-api-management/mobile-sdk-for-ca-mobile-api-gateway/2-0.html
 [StackOverflow]: http://stackoverflow.com/questions/tagged/massdk
 [download]: https://github.com/CAAPIM/iOS-MAS-Proximity/archive/master.zip
 [contributing]: https://github.com/CAAPIM/iOS-MAS-Connecta/blob/develop/CONTRIBUTING.md
 [license-link]: /LICENSE
