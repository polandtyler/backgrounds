//
//  FNPasswordKeychainItem.h
//  FNFoundation
//
//  Created by Alexander Rinass on 09.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNKeychainItem.h"

@interface FNPasswordKeychainItem : FNKeychainItem
// The date the item was created.
@property (nonatomic, readonly) NSDate *creationDate;

// The last time the item was updated.
@property (nonatomic, readonly) NSDate *modificationDate;

// Specifies a user-visible string describing this kind of item (for example,
// "Disk image password").
@property (nonatomic, copy) NSString *userDescription;

// Contains the user-editable comment for this item.
@property (nonatomic, copy) NSString *comment;

// This number is the unsigned integer representation of a four-character
// code (for example, 'aCrt').
@property (nonatomic) NSUInteger creator;

// This number is the unsigned integer representation of a four-character
// code (for example, 'aTyp').
//@property (nonatomic, assign) NSUInteger type;

// Whether or not the item is invisible (that is, should not be displayed).
@property (nonatomic, getter = isInvisible) BOOL invisible;

// Indicates whether there is a valid password associated with this keychain item.
// This is useful if your application doesn't want a password for some particular
// service to be stored in the keychain, but prefers that it always be entered by the user.
@property (nonatomic, getter = isNegative) BOOL negative;

// Contains an account name
@property (nonatomic, copy) NSString *account;

// Contains the password
@property (nonatomic, copy) NSString *password;

@end
