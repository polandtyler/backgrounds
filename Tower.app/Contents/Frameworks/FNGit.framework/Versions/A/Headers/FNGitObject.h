//
//  FNGitObject.h
//  FNGit
//
//  Created by Alexander Rinass on 20.05.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>
#import "FNGitDefines.h"

@class FNGitRepository;
@interface FNGitObject : NSObject
@property (nonatomic, weak, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) FNGitObjectType objectType;
@property (nonatomic, readonly) NSString *objectHash;
@property (nonatomic, readonly) NSString *shortObjectHash;
@property (nonatomic, readonly) BOOL isBlobObject;
@property (nonatomic, readonly) BOOL isTreeObject;
@property (nonatomic, readonly) BOOL isCommitObject;
@property (nonatomic, readonly) BOOL isTagObject;

#pragma mark - Creating Object Identifiers

+ (NSString *)objectReferenceWithRevision:(NSString *)revision filePath:(NSString *)filePath;

#pragma mark - Abbreviating Object Hashes

+ (NSString *)shortenObjectHash:(NSString *)objectHash;
+ (NSString *)shortenObjectHash:(NSString *)objectHash withLength:(NSUInteger)length;

#pragma mark - Is an Object Hash a Null Object Hash

+ (BOOL)isNullObjectHash:(NSString *)objectHash;

#pragma mark - String Representation for Object Types

+ (NSString *)stringRepresentationForObjectType:(FNGitObjectType)objectType;

#pragma mark - Object Type From String

+ (FNGitObjectType)objectTypeFromString:(NSString *)objectTypeString;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository objectType:(FNGitObjectType)objectType objectHash:(NSString *)objectHash;

#pragma mark - Deprecated

+ (NSString *)abbreviateObjectHash:(NSString *)objectHash __deprecated;
+ (NSString *)stringRepresentationForFileMode:(FNGitFileMode)fileMode __deprecated;
+ (FNGitFileMode)fileModeFromString:(NSString *)fileModeString __deprecated;

@end
