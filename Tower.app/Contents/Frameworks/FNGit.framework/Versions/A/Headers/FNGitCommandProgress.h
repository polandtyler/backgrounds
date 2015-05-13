//
//  FNGitProgressOutput.h
//  FNGit
//
//  Created by Alexander Rinass on 30.06.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>

@interface FNGitCommandProgress : NSObject

/** @name Creating Instances */

/**
 Creates and returns an empty command progress.
 */
- (instancetype)initWithCommand:(NSString *)command;

/**
 The name of the Git command.
 */
@property (nonatomic, readonly) NSString *command;

/** @name Querying the Progress Output */

/**
 Returns the current progress output.
 
 This mimics the output given on the command line when invoking Git commands that produce progress
 output (e.g. clone, fetch, ...).
 */
@property (atomic, readonly) NSString *currentProgressOutput;

/**
 Returns the last line of progress output suitable for display in a single line text field.
 */
@property (atomic, readonly) NSString *lastProgressOutputLine;

/**
 Returns the line count of the current progress.
 */
@property (atomic, readonly) NSUInteger lineCount;

/**
 Returns the overall progress of a command progress.
 
 Values range from 0.0 to 1.0.
 */
@property (atomic, readonly) double overallProgress;

/**
 Wether or not the command introduced changes.
 */
@property (nonatomic, readonly, getter = isUpdated) BOOL updated;

@property (nonatomic, readonly, getter = isIndeterminate) BOOL indeterminate;

/** @name Updating and Finishing the Progress */

/**
 Updates the progress with the given output data.
 */
- (void)updateProgressWithOutputData:(NSData *)outputData;

/**
 Updates the progress with the given output string.
 */
- (void)updateProgressWithOutputString:(NSString *)outputString;

/**
 Marks the progress as finished. This will set the overall progress to its
 maximum value.
 */
- (void)finishProgress;

/** @name Resetting the Progress */

/**
 Resets the command progress.
 */
- (void)reset;

@end
