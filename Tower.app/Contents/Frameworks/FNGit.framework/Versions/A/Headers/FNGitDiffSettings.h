//
//  FNGitChangesetDiffSettings.h
//  FNGit
//
//  Created by Alexander Rinass on 13.07.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FNGitDiffSettings : NSObject
@property (nonatomic, copy) NSArray *revisions;
@property (nonatomic, copy) NSDictionary *logOptions;
@property (nonatomic, copy) NSDictionary *diffOptions;
@end
