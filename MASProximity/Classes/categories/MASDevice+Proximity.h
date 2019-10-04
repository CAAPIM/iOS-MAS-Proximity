//
//  MASDevice+Proximity.h
//  MASProximity
//
//  Copyright (c) 2019 CA. All rights reserved.
//
//  This software may be modified and distributed under the terms
//  of the MIT license. See the LICENSE file for details.
//

#import <MASFoundation/MASFoundation.h>


@class MASAuthenticationProvider;

@protocol MASProximityLoginDelegate;


@interface MASDevice (Proximity)

///--------------------------------------
/// @name Properties
///--------------------------------------

# pragma mark - Properties

/**
 *  The MASProximityLoginDelegate static property getter
 */
+ (id<MASProximityLoginDelegate> _Nullable)proximityLoginDelegate;


/**
 *  The MASProximityLoginDelegate static property setter
 */
+ (void)setProximityLoginDelegate:(id<MASProximityLoginDelegate> _Nonnull)delegate;



///--------------------------------------
/// @name Bluetooth Peripheral
///--------------------------------------

# pragma mark - Bluetooth Peripheral

/**
 * Start the device acting as a bluetooth peripheral.
 */
- (void)startAsBluetoothPeripheral;



/**
 * Stop the device acting as a bluetooth peripheral.
 */
- (void)stopAsBluetoothPeripheral;



///--------------------------------------
/// @name Bluetooth Central
///--------------------------------------

# pragma mark - Bluetooth Central

/**
 *  Start the device acting as a bluetooth central.
 */
- (void)startAsBluetoothCentral;



/**
 *  Start the device acting as a bluetooth central with given authentication provider.
 *
 *  @param provider MASAuthenticationProvider to pass authentication information to other devices
 */
- (void)startAsBluetoothCentralWithAuthenticationProvider:(MASAuthenticationProvider *_Nonnull)provider;



/**
 * Stop the device acting as a bluetooth central.
 */
- (void)stopAsBluetoothCentral;

@end
