//
//  FNGitTreeIsh.h
//  FNGit
//
//  Created by Alexander Rinaß on 08.03.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNGitTree;
@protocol FNGitTreeIsh <NSObject>
@property (nonatomic, readonly) NSString *treeHash;

- (FNGitTree *)tree;

@end
