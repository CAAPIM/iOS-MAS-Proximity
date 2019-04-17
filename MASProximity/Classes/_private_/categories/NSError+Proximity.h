//
//  NSError+Proximity.h
//  MASProximity
//
//  Copyright (c) 2019 CA. All rights reserved.
//
//  This software may be modified and distributed under the terms
//  of the MIT license. See the LICENSE file for details.
//

#import <Foundation/Foundation.h>

#import "MASProximityConstantsPrivate.h"
#import "MASProximityError.h"

@interface NSError (Proximity)

/**
 * Creates an NSError for the given MASProximityErrorCode.  These errors will fall
 * under the specified domain in parameter.
 *
 * This version is a convenience version without the info:(NSDictionary *)info
 * parameter for those that don't need to add any custom info.
 *
 * All errors will include the following standard keys with applicable values:
 *
 *    NSLocalizedDescriptionKey
 *
 * @param errorCode The MASUIErrorCode which identifies the error.
 * @param errorDomain The NSString of error domain.
 * @returns Returns the NSError instance.
 */
+ (NSError *)errorForProximityErrorCode:(MASProximityErrorCode)errorCode errorDomain:(NSString *)errorDomain;



/**
 * Creates an NSError for the given MASProximityErrorCode.  These errors will fall
 * under the sepcified domain in parameter.
 *
 * All errors will include the following standard keys with applicable values:
 *
 *    NSLocalizedDescriptionKey
 *
 * @param errorCode The MASUIErrorCode which identifies the error.
 * @param info An additional NSDictionary of custom values that can be included
 * in addition to the defaults included by this method.  Optional, nil is allowed.
 * @param errorDomain The NSString which identifies the domain of the error.
 * @returns Returns the NSError instance.
 */
+ (NSError *)errorForProximityErrorCode:(MASProximityErrorCode)errorCode info:(NSDictionary *)info errorDomain:(NSString *)errorDomain;


/**
 *  Create MASProximityErrorDomainLocal NSError for MASFoundationErrorCodeProximityLoginAuthorizationInProgress.
 *
 *  @return Returns an NSError instance with the domain MASProximityErrorDomainLocal and
 *  error MASFoundationErrorCodeProximityLoginAuthorizationInProgress.
 */
+ (NSError *)errorProximityLoginAuthorizationInProgress;


/**
 *  Create MASProximityErrorDomainLocal NSError for MASFoundationErrorCodeProximityLoginInvalidAuthorizeURL.
 *
 *  @return Returns an NSError instance with the domain MASProximityErrorDomainLocal and
 *  error MASFoundationErrorCodeProximityLoginInvalidAuthorizeURL
 */
+ (NSError *)errorProximityLoginInvalidAuthroizeURL;


/**
 * Create MASProximityErrorDomainLocal NSError for MASProximityErrorCodeInvalidAuthorization.
 *
 * @returns Returns an NSError instance with the domain MASProximityErrorDomainLocal and
 * error code MASProximityErrorCodeInvalidAuthorization.
 */
+ (NSError *)errorInvalidAuthorization;

@end
