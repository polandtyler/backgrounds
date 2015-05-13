//
//  NSURL+FNFinderAlias.h
//  FNFoundation
//
//  Created by Alexander Rinass on 22/01/15.
//  Copyright (c) 2015 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSURL (FNFinderAlias)

+ (instancetype)fileURLFromAliasAtURL:(NSURL *)aliasFileURL error:(NSError * __autoreleasing *)error;

@end
