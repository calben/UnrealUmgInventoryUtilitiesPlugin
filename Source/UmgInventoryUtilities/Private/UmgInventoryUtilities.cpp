// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "UmgInventoryUtilities.h"

#define LOCTEXT_NAMESPACE "FUmgInventoryUtilitiesModule"

DEFINE_LOG_CATEGORY(LogUmgInventoryUtilties);

void FUmgInventoryUtilitiesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FUmgInventoryUtilitiesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUmgInventoryUtilitiesModule, UmgInventoryUtilities)