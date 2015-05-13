//
//  FNGitRemoteBranchParser.h
//  FNGit
//
//  Created by Alexander Rinass on 17.06.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import "FNGitOutputParser.h"
#import "FNGitRemoteBranchOutputParserResultItem.h"

@interface FNGitRemoteBranchOutputParser : FNGitOutputParser
@property (nonatomic, readonly) NSArray *remoteBranches;
@end
