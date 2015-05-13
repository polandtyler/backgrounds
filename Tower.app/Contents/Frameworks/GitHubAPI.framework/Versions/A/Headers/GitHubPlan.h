//
//  GitHubPlan.h
//  Tower
//
//  Created by Alexander Rinass on 12.04.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>

@interface GitHubPlan : NSObject <NSCopying>
@property (nonatomic, strong, readonly) NSString *name;
@property (nonatomic, readonly) NSInteger space;
@property (nonatomic, readonly) NSInteger collaborators;
@property (nonatomic, readonly) NSInteger privateRepositories;

#pragma mark - Factory Methods

+ (id)planFromJSONObject:(NSDictionary *)JSONObject;

#pragma mark - Comparing Objects

- (BOOL)isEqualToGitHubPlan:(GitHubPlan *)otherObject;

@end
