//
//  FNGitShowRefCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 30.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

extern NSString *const FNGitShowRefOptionHead;
extern NSString *const FNGitShowRefOptionHeads;
extern NSString *const FNGitShowRefOptionTags;

@interface FNGitShowRefCommand : FNGitCommand
@property (nonatomic) BOOL showsHead;
@property (nonatomic) BOOL showsHeads;
@property (nonatomic) BOOL showsTags;
@property (nonatomic) BOOL showsHashesOnly;
@property (nonatomic, readonly) NSArray *refs;

#pragma mark - Factory Methods

+ (id)gitShowRefCommandWithRepository:(FNGitRepository *)repository options:(NSDictionary *)options;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository options:(NSDictionary *)options;

@end
