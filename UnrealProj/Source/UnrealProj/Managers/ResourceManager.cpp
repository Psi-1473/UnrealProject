// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceManager.h"
#include "PoolManager.h"

FString UResourceManager::GetClassNameFromDir(FString Dir)
{
	int startIndex = 0;
	int lastIndex = Dir.Len() -1;
	Dir.FindLastChar('.', startIndex);
	startIndex++;
	FString ClassName = Dir.Mid(startIndex);
	ClassName = ClassName.Mid(0, ClassName.Len() - 1);
	UE_LOG(LogTemp, Warning, TEXT("Class Name Test : %s"), *ClassName);

	return ClassName;
}
