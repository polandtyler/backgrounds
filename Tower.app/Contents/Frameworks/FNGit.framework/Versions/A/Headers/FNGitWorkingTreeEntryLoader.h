//
//  FNGitWorkingTreeEntryLoader.h
//  FNGit
//
//  Created by Alexander Rinass on 06.12.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>

@class FNGitRepository;
@interface FNGitWorkingTreeEntryLoader : NSObject
@property (nonatomic, readonly) FNGitRepository *repository;

/** @name Creating Submodule Loader Objects */

+ (id)loaderWithRepository:(FNGitRepository *)repository;
- (id)initWithRepository:(FNGitRepository *)repository;

/** @name Loading WorkingTreeEntries */

- (NSArray *)loadWorkingTreeEntriesForFilePath:(NSString *)filePath options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

@end
