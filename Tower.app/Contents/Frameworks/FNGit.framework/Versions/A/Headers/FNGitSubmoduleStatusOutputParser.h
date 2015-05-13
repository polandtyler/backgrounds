//
//  FNGitSubmoduleStatusParser.h
//  FNGit
//
//  Created by Alexander Rinass on 26.07.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import "FNGitOutputParser.h"
#import "FNGitSubmoduleOutputParserResultItem.h"

@interface FNGitSubmoduleStatusOutputParser : FNGitOutputParser

- (NSArray *)result;

@end
