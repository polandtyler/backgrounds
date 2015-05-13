//
//  FNGitTag.h
//  FNGit
//
//  Created by Alexander Rinass on 06.12.10.
//  Copyright 2010 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitObject.h"
#import "FNGitRef.h"

@class FNGitRepository;
@class FNGitCommit;
@interface FNGitTag : FNGitObject <FNGitRef>
@property (nonatomic, readonly) FNGitRef *ref;
@property (nonatomic, readonly) NSString *fullRefName;
@property (nonatomic, readonly) NSString *refName;
@property (nonatomic, readonly) NSString *commitHash;
@property (nonatomic, readonly) FNGitCommit *commit;
@property (nonatomic, readonly) BOOL isAnnotatedTag;
@property (nonatomic, readonly) NSString *message;

#pragma mark - Retrieving Tags From a Repository

+ (NSArray *)allTagsForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (id)tagForRefName:(NSString *)refName repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Creating a New Tag in a Repository

+ (id)createTagWithRefName:(NSString *)refName fromRevision:(NSString *)revision inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (id)createTagWithRefName:(NSString *)refName message:(NSString *)message fromRevision:(NSString *)revision inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Deleting a Tag in a Repository

+ (BOOL)deleteTagWithRefName:(NSString *)refName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Factory Methods

+ (id)tagWithRepository:(FNGitRepository *)repository ref:(FNGitRef *)ref;
+ (id)tagWithRepository:(FNGitRepository *)repository ref:(FNGitRef *)ref objectHash:(NSString *)objectHash;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository ref:(FNGitRef *)ref;
- (id)initWithRepository:(FNGitRepository *)repository ref:(FNGitRef *)ref objectHash:(NSString *)objectHash;

@end
