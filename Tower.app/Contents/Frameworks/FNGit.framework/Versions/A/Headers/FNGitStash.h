//
//  FNGitStash.h
//  FNGit
//
//  Created by Alexander Rinass on 06.12.10.
//  Copyright 2010 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitRef.h"

@class FNGitRepository;
@class FNGitCommit;
@interface FNGitStash : NSObject <FNGitRef>
@property (nonatomic, weak, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) FNGitRef *ref;
@property (nonatomic, readonly) NSString *fullRefName;
@property (nonatomic, readonly) NSString *refName;
@property (nonatomic, readonly) NSString *commitHash;
@property (nonatomic, readonly) NSDate *creationDate;
@property (nonatomic, readonly) FNGitCommit *commit;
@property (nonatomic, readonly) NSUInteger index;
@property (nonatomic, readonly) NSString *message;
@property (nonatomic, readonly) NSString *userMessage;
@property (nonatomic, readonly) NSString *originBranch;
@property (nonatomic, readonly) NSString *indexCommitHash;
@property (nonatomic, readonly) NSString *untrackedFilesCommitHash;
@property (nonatomic, readonly) NSString *originCommitHash;

#pragma mark - Creating Stash Ref Names

+ (NSString *)makeFullRefNameWithStashIndex:(NSUInteger)index;

#pragma mark - Retrieving Stashes

+ (NSArray *)allStashesForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (id)stashForRefName:(NSString *)refName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (id)stashAtIndex:(NSUInteger)index inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Creating New Stashes

+ (id)createStashFromWorkingTreeInRepository:(FNGitRepository *)repository withMessage:(NSString *)message error:(NSError * __autoreleasing *)error;

#pragma mark - Deleting the Stash

+ (BOOL)deleteStashAtIndex:(NSUInteger)index inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (BOOL)deleteStashWithRefName:(NSString *)refName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Applying the Stash to the Working Tree

+ (BOOL)applyStashAtIndex:(NSUInteger)index toWorkingTreeInRepository:(FNGitRepository *)repository deletingStash:(BOOL)deletesStash error:(NSError * __autoreleasing *)error;
+ (BOOL)applyStashWithRefName:(NSString *)refName toWorkingTreeInRepository:(FNGitRepository *)repository deletingStash:(BOOL)deletesStash error:(NSError * __autoreleasing *)error;

#pragma mark - Factory Methods

+ (id)stashWithRepository:(FNGitRepository *)repository ref:(FNGitRef *)ref;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository ref:(FNGitRef *)ref;

@end
