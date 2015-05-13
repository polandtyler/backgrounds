//
//  NSDictionary+FNCommon.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 20.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSDictionary (FNCommon)

- (BOOL)isEmpty;
- (BOOL)existsKey:(NSString *)key;
- (BOOL)containsObjectForKey:(NSString *)key;

- (NSDictionary *)dictionaryByAddingEntriesFromDictionary:(NSDictionary *)dictionary;

@end
