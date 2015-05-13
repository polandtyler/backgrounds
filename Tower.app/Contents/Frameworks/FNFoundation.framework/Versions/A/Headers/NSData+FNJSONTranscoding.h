//
//  NSData+FNJSONTranscoding.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 22.05.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSData (FNJSONTranscoding)

+ (id)dataWithJSONObject:(id)JSONObject error:(NSError * __autoreleasing *)error;
- (id)JSONObject:(NSError * __autoreleasing *)error;

@end
