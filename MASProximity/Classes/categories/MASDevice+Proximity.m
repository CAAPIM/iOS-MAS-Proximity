//
//  MASDevice+Proximity.m
//  MASProximity
//
//  Copyright (c) 2019 CA. All rights reserved.
//
//  This software may be modified and distributed under the terms
//  of the MIT license. See the LICENSE file for details.
//

#import "MASDevice+Proximity.h"

#import "MASBluetoothCentral.h"
#import "MASBluetoothPeripheral.h"
#import "MASBluetoothService.h"

@implementation MASDevice (Proximity)

static id<MASProximityLoginDelegate> _proximityLoginDelegate_;


# pragma mark - Property

+ (id<MASProximityLoginDelegate>)proximityLoginDelegate
{
    return _proximityLoginDelegate_;
}


+ (void)setProximityLoginDelegate:(id<MASProximityLoginDelegate>)delegate
{
    _proximityLoginDelegate_ = delegate;
}


# pragma mark - Bluetooth Peripheral

- (void)startAsBluetoothPeripheral
{
    [[MASBluetoothService sharedService].peripheral startAdvertising];
}


- (void)stopAsBluetoothPeripheral
{
    [[MASBluetoothService sharedService].peripheral stopAdvertising];
}


# pragma mark - Bluetooth Central

- (void)startAsBluetoothCentral
{
    [[MASBluetoothService sharedService].central startScanning];
}


- (void)startAsBluetoothCentralWithAuthenticationProvider:(MASAuthenticationProvider *)provider
{
    [[MASBluetoothService sharedService].central startScanningWithAuthenticationProvider:provider];
}


- (void)stopAsBluetoothCentral
{
    [[MASBluetoothService sharedService].central stopScanning];
}


@end
