// Fill out your copyright notice in the Description page of Project Settings.


#include "HitCameraShake.h"

UHitCameraShake::UHitCameraShake()
{
	OscillationDuration = 0.2f; // 몇 초 동안 실행할 것인가
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.05f;

	// Amplitude 진폭
	// Frequency 빈도

	RotOscillation.Pitch.Amplitude = FMath::RandRange(2.0f, 3.0f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(5.0f, 10.0f);

	RotOscillation.Yaw.Amplitude = FMath::RandRange(1.0f, 2.0f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(1.0f, 5.0f);

	// true로 해줘야 한번씩만 떨림
	bSingleInstance = true;
}

