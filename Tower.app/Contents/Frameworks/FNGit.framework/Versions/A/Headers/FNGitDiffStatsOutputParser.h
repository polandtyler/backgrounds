//
//  FNGitDiffStatsParser.h
//  FNGit
//
//  Created by Alexander Rinass on 11.07.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import "FNGitOutputParser.h"
#import "FNGitDiffStatsOutputParserResultItem.h"

@interface FNGitDiffStatsOutputParser : FNGitOutputParser
@property (nonatomic, readonly) NSArray *result;
@end
