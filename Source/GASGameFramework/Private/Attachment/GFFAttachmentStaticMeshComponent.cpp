// Fill out your copyright notice in the Description page of Project Settings.


#include "Attachment/GFFAttachmentStaticMeshComponent.h"

#include "Logging.h"

UGFFAttachmentStaticMeshComponent::UGFFAttachmentStaticMeshComponent()
{
    bUseDefaultCollision = false;
    BodyInstance.SetCollisionProfileName("CharacterMesh");
}

void UGFFAttachmentStaticMeshComponent::SetMesh_Implementation(UStreamableRenderAsset* Mesh)
{
    // null 검사
    if(Mesh == nullptr) return;

    // 스태틱 메시인지 확인
    if(!Mesh->IsA(UStaticMesh::StaticClass()))
    {
#if WITH_EDITOR
        LOG_CALLINFO_COMMENT(LogGASGameFramework, Warning, TEXT("%s는 스태틱 메시가 아닙니다."), *Mesh->GetName())
#endif
        return;
    }

    // 스태틱 메시 에셋 설정
    SetStaticMesh(Cast<UStaticMesh>(Mesh));
}
