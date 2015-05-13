//
//  FNViewDefaults.h
//  FNAppKit
//
//  Created by Alexander Rinass on 08.07.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *const FNViewDefaultsDidChangeNotification;

@interface FNViewDefaults : NSObject

/** @name Creating View Styles Objects */

+ (instancetype)sharedDefaults;
- (id)initWithDictionary:(NSDictionary *)dictionary;

/** @name Getting and Setting Values */

- (NSString *)stringForKey:(NSString *)key;
- (void)setString:(NSString *)string forKey:(NSString *)key;

- (BOOL)boolForKey:(NSString *)key;
- (void)setBool:(BOOL)value forKey:(NSString *)key;

- (NSInteger)integerForKey:(NSString *)key;
- (void)setInteger:(NSInteger)value forKey:(NSString *)key;

- (CGFloat)floatForKey:(NSString *)key;
- (void)setFloat:(CGFloat)value forKey:(NSString *)key;

- (NSColor *)colorForKey:(NSString *)key;
- (void)setColor:(NSColor *)color forKey:(NSString *)key;

- (NSArray *)colorsForKey:(NSString *)key;
- (void)setColors:(NSArray *)colors forKey:(NSString *)key;

- (NSFont *)fontForKey:(NSString *)key;
- (void)setFont:(NSFont *)font forKey:(NSString *)key;

- (NSImage *)imageForKey:(NSString *)key;
- (void)setImage:(NSImage *)image forKey:(NSString *)key;

- (NSTimeInterval)timeIntervalForKey:(NSString *)key;
- (void)setTimeInterval:(NSTimeInterval)value forKey:(NSString *)key;

- (NSSize)sizeForKey:(NSString *)key;
- (void)setSize:(NSSize)size forKey:(NSString *)key;

- (NSPoint)pointForKey:(NSString *)key;
- (void)setPoint:(NSPoint)point forKey:(NSString *)key;

- (NSEdgeInsets)edgeInsetsForKey:(NSString *)key;
- (void)setEdgeInsets:(NSEdgeInsets)edgeInsets forKey:(NSString *)key;

- (NSDictionary *)textAttributesForKey:(NSString *)key;
- (void)setTextAttributes:(NSDictionary *)textAttributes forKey:(NSString *)key;

- (NSShadow *)shadowForKey:(NSString *)key;
- (void)setShadow:(NSShadow *)shadow forKey:(NSString *)key;

- (NSGradient *)gradientForKey:(NSString *)key;
- (void)setGradient:(NSGradient *)gradient forKey:(NSString *)key;

/** @name Managing Objects */

- (id)objectForKey:(NSString *)key;
- (void)setObject:(id)object forKey:(NSString *)key;
- (void)removeObjectForKey:(NSString *)key;
- (BOOL)hasObjectForKey:(NSString *)key;

/** @name Retrieving Dictionary Representation */

- (NSDictionary *)dictionaryRepresentation;

- (void)clearCache;

@end
