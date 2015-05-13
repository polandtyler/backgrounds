//
//  NSFileManager+FNFileTypes.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 20.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSFileManager (FNFileTypes)

+ (NSString *)humanReadableFileTypeForFileAtPath:(NSString *)path;
+ (NSString *)MIMETypeForFileAtPath:(NSString *)filePath;

@end
