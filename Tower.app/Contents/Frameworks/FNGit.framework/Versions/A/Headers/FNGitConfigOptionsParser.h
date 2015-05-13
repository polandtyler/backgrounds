//
//  FNGitConfigOutputParser.h
//  FNGit
//
//  Created by Alexander Rinass on 30.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitOutputParser.h"

@interface FNGitConfigOptionsParser : FNGitOutputParser
@property (nonatomic, readonly) NSDictionary *configOptions;

#pragma mark - Parsing Config Options By Section

+ (NSDictionary *)parseConfigOptionsBySection:(NSDictionary *)configOptions;

@end
