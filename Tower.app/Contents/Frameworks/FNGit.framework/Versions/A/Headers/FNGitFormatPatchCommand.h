//
//  FNGitFormatPatchCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 19/08/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <FNGit/FNGit.h>

@interface FNGitFormatPatchCommand : FNGitCommand
@property (nonatomic) NSArray *revisions;
@property (nonatomic) NSURL *destinationURL;
@property (nonatomic) NSUInteger startingNumber;
@property (nonatomic) BOOL numbersPatches;
@property (nonatomic, readonly) NSArray *createdPatchFilePaths;

+ (id)gitFormatPatchCommandWithRepository:(FNGitRepository *)repository revisions:(NSArray *)revisions options:(NSDictionary *)options;
- (id)initWithRepository:(FNGitRepository *)repository revisions:(NSArray *)revisions options:(NSDictionary *)options;

@end
