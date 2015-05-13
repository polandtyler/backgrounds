//
//  FNGitCommitIsh.h
//  FNGit
//
//  Created by Alexander Rinass on 12.07.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNGitCommit;
@protocol FNGitCommitIsh <NSObject>
@property (nonatomic, readonly) NSString *commitHash;

- (FNGitCommit *)commit;

@end
