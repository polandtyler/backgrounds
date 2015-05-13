//
//  BeanstalkRepository.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 12.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *const BeanstalkVCSTypeSubversion;
extern NSString *const BeanstalkVCSTypeGit;
extern NSString *const BeanstalkVCSTypeMercurial;

extern NSString *const BeanstalkColorLabelRed;
extern NSString *const BeanstalkColorLabelOrange;
extern NSString *const BeanstalkColorLabelYellow;
extern NSString *const BeanstalkColorLabelGreen;
extern NSString *const BeanstalkColorLabelBlue;
extern NSString *const BeanstalkColorLabelPink;
extern NSString *const BeanstalkColorLabelGrey;

@interface BeanstalkRepository : NSObject <NSCopying>
@property (nonatomic, readonly) NSInteger repositoryID;
@property (nonatomic, readonly) NSInteger accountID;
@property (nonatomic, strong) NSString *title;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *colorLabel;
@property (nonatomic, strong) NSString *defaultBranch;
@property (nonatomic, strong) NSString *type;
@property (nonatomic, strong, readonly) NSString *repositoryURL;
@property (nonatomic, strong, readonly) NSDate *lastCommitAt;
@property (nonatomic, strong, readonly) NSDate *updatedAt;
@property (nonatomic, strong, readonly) NSDate *createdAt;

#pragma mark - Factory Methods

+ (id)repositoryFromJSONObject:(NSDictionary *)JSONObject;

#pragma mark - Retrieving Writable JSON Properties

- (NSDictionary *)writableJSONProperties;

#pragma mark - Comparing Objects

- (BOOL)isEqualToBeanstalkRepository:(BeanstalkRepository *)otherObject;

@end
