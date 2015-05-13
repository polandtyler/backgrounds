//
//  FNGitChangesetLoader.h
//  FNGit
//
//  Created by Alexander Rinass on 15.08.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNGitDiff;
@class FNGitChangeset;
@class FNGitRepository;
@interface FNGitChangesetLoader : NSObject
@property (nonatomic, readonly) FNGitRepository *repository;
@property (nonatomic, copy) NSArray *revisions;
@property (nonatomic, copy) NSArray *filePaths;
@property (nonatomic, copy) NSDictionary *logOptions;
@property (nonatomic, copy) NSDictionary *diffOptions;

/** @name Creating Changeset Loader Objects */

+ (id)loaderWithRepository:(FNGitRepository *)repository;
- (id)initWithRepository:(FNGitRepository *)repository;

/** @name Loading Changesets */

/**
 Loads the changeset with the configured options.
 */
- (FNGitChangeset *)loadChangeset:(NSError * __autoreleasing *)error;

@end
