//
//  NSString+FNSearching.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 20.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (FNSearching)

- (BOOL)containsString:(NSString *)string;

- (BOOL)containsStringSearchingInsensitive:(NSString *)string;
- (BOOL)containsString:(NSString *)string options:(NSStringCompareOptions)options;

@end
