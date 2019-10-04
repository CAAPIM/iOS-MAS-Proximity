//
//  NSError+Proximity.m
//  MASProximity
//
//  Copyright (c) 2019 CA. All rights reserved.
//
//  This software may be modified and distributed under the terms
//  of the MIT license. See the LICENSE file for details.
//

#import "NSError+Proximity.h"

@implementation NSError (Proximity)


+ (NSError *)errorProximityLoginAuthorizationInProgress
{
    return [self errorForProximityErrorCode:MASProximityErrorCodeAuthorizationInProgress errorDomain:MASProximityErrorDomainLocal];
}


+ (NSError *)errorProximityLoginInvalidAuthroizeURL
{
    return [self errorForProximityErrorCode:MASProximityErrorCodeInvalidAuthorizeURL errorDomain:MASProximityErrorDomainLocal];
}


+ (NSError *)errorInvalidAuthorization
{
    return [self errorForProximityErrorCode:MASProximityErrorCodeInvalidAuthorization errorDomain:MASProximityErrorDomainLocal];
}


+ (NSError *)errorForProximityErrorCode:(MASProximityErrorCode)errorCode errorDomain:(NSString *)errorDomain
{
    return [self errorForProximityErrorCode:errorCode info:nil errorDomain:errorDomain];
}


+ (NSError *)errorForProximityErrorCode:(MASProximityErrorCode)errorCode info:(NSDictionary *)info errorDomain:(NSString *)errorDomain
{
    //
    // Standard error key/values
    //
    NSMutableDictionary *errorInfo = [NSMutableDictionary new];
    if(![info objectForKey:NSLocalizedDescriptionKey])
    {
        errorInfo[NSLocalizedDescriptionKey] = [self descriptionForProximityErrorCode:errorCode];
    }
    
    [errorInfo addEntriesFromDictionary:info];
    
    return [NSError errorWithDomain:errorDomain code:errorCode userInfo:errorInfo];
}


+ (NSString *)descriptionForProximityErrorCode:(MASProximityErrorCode)errorCode
{
    //
    // Detect code and respond appropriately
    //
    switch(errorCode)
    {
            //
            // Default
            //
        case MASProximityErrorCodeAuthorizationInProgress:
            return @"Authorization is currently in progress through proximity login.";
            break;
        case MASProximityErrorCodeInvalidAuthenticationURL:
            return @"Invalid authentication URL is provided for proximity login.";
            break;
        case MASProximityErrorCodeQRCodeAuthorizationPollingFailed:
            return @"QR Code proximity login authentication failed with specific information on userInfo.";
            break;
        case MASProximityErrorCodeInvalidAuthorizeURL:
            return @"Invalid authorization url.";
            break;
            
            //
            // BLE
            //
        case MASProximityErrorCodeBLEUnknownState:
            return @"Unknown error occurred while enabling BLE Central";
            break;
        case MASProximityErrorCodeBLEPoweredOff:
            return @"Bluetooth is currently off";
            break;
        case MASProximityErrorCodeBLEResetting:
            return @"Bluetooth connection is momentarily lost; resetting the connection";
            break;
        case MASProximityErrorCodeBLEUnauthorized:
            return @"Bluetooth feature is not authorized for this application";
            break;
        case MASProximityErrorCodeBLEUnSupported:
            return @"Bluetooth feature is not supported";
            break;
        case MASProximityErrorCodeBLEDelegateNotDefined:
            return @"MASDevice's BLE delegate is not defined. Delegate is mandatory to acquire permission from the user.";
            break;
        case MASProximityErrorCodeBLEAuthorizationFailed:
            return @"BLE authorization failed due to invalid or expired authorization request.";
            break;
        case MASProximityErrorCodeBLECentralDeviceNotFound:
            return @"BLE authorization failed due to no subscribed central device.";
            break;
        case MASProximityErrorCodeBLERSSINotInRange:
            return @"BLE RSSI is not in range.  Please refer to msso_config.json for BLE RSSI configuration.";
            break;
        case MASProximityErrorCodeBLEAuthorizationPollingFailed:
            return @"BLE authorization failed while polling authorization code from gateway.";
            break;
        case MASProximityErrorCodeBLEInvalidAuthenticationProvider:
            return @"BLE authorization failed due to invalid authentication provider.";
            break;
        case MASProximityErrorCodeBLECentral:
            return @"BLE Central error encountered in CBCentral with specific reason in userInfo.";
            break;
        case MASProximityErrorCodeBLEPeripheral:
            return @"BLE Peripheral error encountered while discovering, or connecting central device with specific reason in userInfo.";
            break;
        case MASProximityErrorCodeBLEPeripheralServices:
            return @"BLE Peripheral error encountered while discovering or connecting peripheral services with specific reason in userInfo.";
            break;
        case MASProximityErrorCodeBLEPeripheralCharacteristics:
            return @"BLE Peripheral error encountered while discovering, connecting, or writing peripheral service's characteristics with specific reason in userInfo.";
            break;
            
            //
            // Authorization
            //
        case MASProximityErrorCodeInvalidAuthorization: return @"The authorization failed due to invalid state.";
            
        default: return [NSString stringWithFormat:@"Unrecognized error code of value: %ld", (long)errorCode];
    }
}

@end
