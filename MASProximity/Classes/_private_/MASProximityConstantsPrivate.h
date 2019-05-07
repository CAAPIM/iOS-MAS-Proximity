//
//  MASProximityConstantsPrivate.h
//  MASProximity
//
//  Copyright (c) 2019 CA. All rights reserved.
//
//  This software may be modified and distributed under the terms
//  of the MIT license. See the LICENSE file for details.
//

@import Foundation;

#import "CBCentralManager+MASPrivate.h"
#import "CBPeripheralManager+MASPrivate.h"

/**
 * Void code block.
 */
typedef void (^MASVoidCodeBlock)(void);

# pragma mark - Request/Response/Configuration Constants

static NSString *_Nonnull const MASProximityPKCEStateRequestResponseKey = @"state"; // string
