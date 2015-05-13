//
//  BeanstalkFetchUsersAPIRequestOperation.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 14.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "BeanstalkAPIRequestOperation.h"

typedef void (^BeanstalkFetchUsersErrorHandler)(NSError *error);
typedef void (^BeanstalkFetchUsersCompletionHandler)(NSArray *users);

@interface BeanstalkFetchUsersAPIRequestOperation : BeanstalkAPIRequestOperation
@property (nonatomic, readonly) NSInteger page;
@property (nonatomic, strong, readonly) NSArray *users;
@property (nonatomic, copy) BeanstalkFetchUsersErrorHandler errorHandler;
@property (nonatomic, copy) BeanstalkFetchUsersCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BeanstalkAuth *)auth;
+ (id)requestWithAuth:(BeanstalkAuth *)auth page:(NSInteger)page;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth page:(NSInteger)page;

#pragma mark - Synchronously Sending the Request

- (NSArray *)send:(NSError * __autoreleasing *)error;
    
@end
