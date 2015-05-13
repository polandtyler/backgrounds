//
//  NSString+FNMD5.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 20.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (FNMD5)

- (NSString *)md5 __attribute__((deprecated));
- (NSString *)MD5String;

@end
