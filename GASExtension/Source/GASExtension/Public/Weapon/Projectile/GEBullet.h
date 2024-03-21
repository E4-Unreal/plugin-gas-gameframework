// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEProjectile.h"
#include "GEBullet.generated.h"

UCLASS()
class GASEXTENSION_API AGEBullet : public AGEProjectile
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AGEBullet();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
