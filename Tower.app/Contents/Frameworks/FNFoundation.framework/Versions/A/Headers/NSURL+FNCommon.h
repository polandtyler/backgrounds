//
//  NSURL+FNCommon.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 20.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSURL (FNCommon)

- (NSString *)rawUser;

- (NSURL *)URLBySettingUser:(NSString *)aUsername;
- (NSURL *)URLByRemovingUser;

- (NSURL *)URLByDeletingPath;

@end
