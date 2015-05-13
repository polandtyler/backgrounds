//
//  NSString+FNBase64Transcoding.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 20.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (FNBase64Transcoding)

+ (NSString *)stringWithDataUsingBase64Encoding:(NSData *)data;

- (NSData *)dataUsingBase64Encoding;

@end
