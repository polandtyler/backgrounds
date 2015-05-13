//
//  NSData+FNBase64Transcoding.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 20.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSData (FNBase64Transcoding)

+ (NSData *)dataWithBase64EncodedString:(NSString *)aString;

- (NSString *)encodeBase64 __attribute__((deprecated));
- (NSString *)stringUsingBase64Encoding;

@end
