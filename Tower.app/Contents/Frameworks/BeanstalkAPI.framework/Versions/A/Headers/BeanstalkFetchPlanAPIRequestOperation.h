//
//  BeanstalkFetchPlanAPIRequestOperation.h
//  BeanstalkAPI
//
//  Created by Alexander Rinass on 28.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "BeanstalkAPIRequestOperation.h"

@class BeanstalkPlan;

typedef void (^BeanstalkFetchPlanErrorHandler)(NSError *error);
typedef void (^BeanstalkFetchPlanCompletionHandler)(BeanstalkPlan *plan);

@interface BeanstalkFetchPlanAPIRequestOperation : BeanstalkAPIRequestOperation
@property (nonatomic, readonly) NSInteger planID;
@property (nonatomic, strong, readonly) BeanstalkPlan *plan;
@property (nonatomic, copy) BeanstalkFetchPlanErrorHandler errorHandler;
@property (nonatomic, copy) BeanstalkFetchPlanCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BeanstalkAuth *)auth planID:(NSInteger)planID;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth planID:(NSInteger)planID;

#pragma mark - Synchronously Sending the Request

- (BeanstalkPlan *)send:(NSError * __autoreleasing *)error;

@end
