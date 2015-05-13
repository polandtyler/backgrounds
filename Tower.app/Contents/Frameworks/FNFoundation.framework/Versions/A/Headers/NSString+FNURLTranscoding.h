//
//  NSString+FNURLTranscoding.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 20.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (FNURLTranscoding)

- (NSString *)stringByURLEncodingString;
- (NSString *)stringByURLEncodingStringLeavingCharactersInStringUntoched:(NSString *)anUntouchedCharacterSetString encodingLegalURLCharactersInString:(NSString *)aLegalCharacterSetString;
- (NSString *)stringByURLEncodingIllegalAndCriticalLegalURLCharactersInString;
- (NSString *)stringByURLDecodingString;

@end
