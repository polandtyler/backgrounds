//
//  FNGitCherryPickCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 30.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

@interface FNGitCherryPickCommand : FNGitCommand
@property (nonatomic, copy) NSArray *revisions;
@property (nonatomic) NSUInteger mainlineParentNumber;
@property (nonatomic) BOOL commitsChanges;
@property (nonatomic) BOOL fastForwards;
@property (nonatomic) BOOL continuesProcess;
@property (nonatomic) BOOL abortsProcess;
@property (nonatomic) BOOL quitsProcess;

/** @name Creating Cherry-Pick Command Objects */

+ (id)gitCherryPickCommandWithRepository:(FNGitRepository *)repository options:(NSDictionary *)options;
- (id)initWithRepository:(FNGitRepository *)repository options:(NSDictionary *)options;

@end
