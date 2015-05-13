//
//  NSDictionary+FNJSONTranscoding.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 22.05.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSDictionary (FNJSONTranscoding)

+ (id)dictionaryWithDataUsingJSONEncoding:(NSData *)data error:(NSError * __autoreleasing *)error;

- (NSData *)dataUsingJSONEncoding:(NSError * __autoreleasing *)error;

@end
