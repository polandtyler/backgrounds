//
//  BeanstalkFetchPublicKeysAPIRequestOperation
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 14.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "BeanstalkAPIRequestOperation.h"

typedef void (^BeanstalkFetchPublicKeysErrorHandler)(NSError *error);
typedef void (^BeanstalkFetchPublicKeysCompletionHandler)(NSArray *publicKeys);

@interface BeanstalkFetchPublicKeysAPIRequestOperation : BeanstalkAPIRequestOperation
@property (nonatomic, readonly) NSInteger userID;
@property (nonatomic, strong, readonly) NSArray *publicKeys;
@property (nonatomic, copy) BeanstalkFetchPublicKeysErrorHandler errorHandler;
@property (nonatomic, copy) BeanstalkFetchPublicKeysCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BeanstalkAuth *)auth;
+ (id)requestWithAuth:(BeanstalkAuth *)auth userID:(NSInteger)userID;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth userID:(NSInteger)userID;

#pragma mark - Synchronously Sending the Request

- (NSArray *)send:(NSError * __autoreleasing *)error;

@end

