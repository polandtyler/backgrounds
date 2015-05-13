//
//  NSError+FNKeychain.h
//  FNFoundation
//
//  Created by Alexander Rinass on 09.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *const FNKeychainErrorDomain;

@interface NSError (FNKeychain)

+ (id)keychainErrorFromOSStatus:(OSStatus)status;

@end
