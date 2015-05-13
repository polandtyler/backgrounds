//
//  FNGitRevertCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 27.09.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <FNGit/FNGit.h>

@interface FNGitRevertCommand : FNGitCommand
@property (nonatomic, copy) NSArray *revisions;
@property (nonatomic) NSUInteger mainlineParentNumber;
@property (nonatomic) BOOL commitsChanges;
@property (nonatomic) BOOL fastForwards;
@property (nonatomic) BOOL continuesProcess;
@property (nonatomic) BOOL abortsProcess;
@property (nonatomic) BOOL quitsProcess;

/** @name Creating Revert Command Objects */

+ (id)gitRevertCommandWithRepository:(FNGitRepository *)repository options:(NSDictionary *)options;
- (id)initWithRepository:(FNGitRepository *)repository options:(NSDictionary *)options;

@end
