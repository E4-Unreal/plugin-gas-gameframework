// Fill out your copyright notice in the Description page of Project Settings.


#include "Attachment/GFFAttachmentComponent.h"

UGFFAttachmentComponent::UGFFAttachmentComponent()
{
    bUseDefaultCollision = false;
    BodyInstance.SetCollisionProfileName("CharacterMesh");
}
