//
//  FNGitActor.h
//  FNGit
//
//  Created by Alexander Rinass on 03.12.10.
//  Copyright 2010 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>

@interface FNGitActor : NSObject
@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) NSString *email;
@property (nonatomic, readonly) NSString *identifier;
@property (nonatomic, readonly) NSString *displayName;

#pragma mark - Factory Methods

+ (id)actor;
+ (id)actorWithName:(NSString *)name email:(NSString *)email;

#pragma mark - Display Name and Identifier Helper

+ (id)identifierWithName:(NSString *)name email:(NSString *)email;
+ (id)displayNameWithName:(NSString *)name email:(NSString *)email;

#pragma mark - Initialization

- (id)initWithName:(NSString *)name email:(NSString *)email;

#pragma mark - Comparison

- (BOOL)isEqualToGitActor:(id)object;

@end
