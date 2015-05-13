//
//  FNGitSubmoduleOptions.h
//  FNGit
//
//  Created by Alexander Rinass on 12.08.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

typedef NS_ENUM(NSInteger, FNGitSubmoduleStatus) {
    FNGitSubmoduleStatusNone,
    FNGitSubmoduleStatusClean,
    FNGitSubmoduleStatusMissingConfiguration,
    FNGitSubmoduleStatusMissingWorkingTreePath,
    FNGitSubmoduleStatusMissingGitDirectory,
    FNGitSubmoduleStatusEmpty,
	FNGitSubmoduleStatusUninitialized,
	FNGitSubmoduleStatusUpdated,
    FNGitSubmoduleStatusUnmerged
};

typedef NS_ENUM(NSInteger, FNGitSubmoduleFormat) {
    FNGitSubmoduleFormatNone,
    FNGitSubmoduleFormatDetached,
    FNGitSubmoduleFormatLegacy
};

typedef NS_ENUM(NSInteger, FNGitSubmoduleStatusIgnoreMode) {
    FNGitSubmoduleStatusIgnoreModeNone = 1,     // Show every modification to the submodule working tree or commit pointer
    FNGitSubmoduleStatusIgnoreModeAll,      // Completely ignore the submodule whatever comes
    FNGitSubmoduleStatusIgnoreModeDirty,    // Show as modified only if the commit pointer has changed
    FNGitSubmoduleStatusIgnoreModeUntracked // Show as modified only if modified files are in the working tree, ignoring untracked files
};

typedef NS_ENUM(NSInteger, FNGitSubmoduleUpdateStrategy) {
    FNGitSubmoduleUpdateStrategyNone = 1,
    FNGitSubmoduleUpdateStrategyCheckout,
    FNGitSubmoduleUpdateStrategyMerge,
    FNGitSubmoduleUpdateStrategyRebase
};
