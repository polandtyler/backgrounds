//
//  NSData+FNStringDecoding.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 15.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSData (FNStringDecoding)

- (NSString *)stringUsingUTF8Encoding;

- (NSString *)stringUsingBestEncoding;

@end
