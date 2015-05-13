//
//  FNError.h
//  FNFoundation
//
//  Created by Alexander Rinass on 29/04/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNErrorGenerating.h"

@interface FNErrorManager : NSObject

+ (instancetype)sharedManager;

- (void)addErrorDefinitionsFromJSONResourceAtURL:(NSURL *)resourceURL;
- (void)addErrorDefinitions:(NSDictionary *)errorDefinitions;

- (NSError *)errorWithDomain:(NSString *)domain code:(NSInteger)code userInfo:(NSDictionary *)userInfo;

@end
