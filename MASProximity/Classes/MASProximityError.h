//
//  MASProximityError.h
//  MASProximity
//
//  Copyright (c) 2019 CA. All rights reserved.
//
//  This software may be modified and distributed under the terms
//  of the MIT license. See the LICENSE file for details.
//

#import <Foundation/Foundation.h>

///--------------------------------------
/// @name MAG Error Domains
///--------------------------------------

# pragma mark - MAG Error Domains

/**
 * The NSString error domain used by all MAG server related Proximity level NSErrors.
 */
extern NSString *const _Nonnull MASProximityErrorDomain;

/**
 * The NSString error domain used by all MAG local level NSError related Proximity.
 */
extern NSString *const _Nonnull MASProximityErrorDomainLocal;


///--------------------------------------
/// @name MAG Error codes
///--------------------------------------

# pragma mark - MAG Error codes

/**
 * The enumerated error codes for Proximity level NSErrors.
 */

typedef NS_ENUM (NSUInteger, MASProximityErrorCode)
{
    //
    //  Proximity Login - BLE
    //
    MASProximityErrorCodeBLEUnknownState = 650001,
    MASProximityErrorCodeBLEAuthorizationFailed = 650002,
    MASProximityErrorCodeBLEAuthorizationPollingFailed = 650003,
    MASProximityErrorCodeBLECentralDeviceNotFound = 650004,
    MASProximityErrorCodeBLEDelegateNotDefined = 650005,
    MASProximityErrorCodeBLEInvalidAuthenticationProvider = 650006,
    MASProximityErrorCodeBLEPoweredOff = 650007,
    MASProximityErrorCodeBLEResetting = 650008,
    MASProximityErrorCodeBLERSSINotInRange = 650009,
    MASProximityErrorCodeBLEUnSupported = 650010,
    MASProximityErrorCodeBLEUnauthorized = 650011,
    MASProximityErrorCodeBLEUserDeclined = 650012,
    MASProximityErrorCodeBLECentral = 650013,
    MASProximityErrorCodeBLEPeripheral = 650014,
    MASProximityErrorCodeBLEPeripheralServices = 650015,
    MASProximityErrorCodeBLEPeripheralCharacteristics = 650016,
    
    //
    //  Proximity Login - Authentication/Authorization
    //
    MASProximityErrorCodeAuthorizationInProgress = 650101,
    MASProximityErrorCodeInvalidAuthenticationURL = 650102,
    MASProximityErrorCodeQRCodeAuthorizationPollingFailed = 650103,
    MASProximityErrorCodeInvalidAuthorizeURL = 650104,
    
    //
    //  Authorization
    //
    MASProximityErrorCodeInvalidAuthorization = 651001
};
