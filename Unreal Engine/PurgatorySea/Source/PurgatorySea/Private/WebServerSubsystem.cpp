// Fill out your copyright notice in the Description page of Project Settings.


#include "WebServerSubsystem.h"
#include "HttpServerModule.h"
#include "IHttpRouter.h"

FWebServerSubsystem::FWebServerSubsystem()
{
}

FWebServerSubsystem::~FWebServerSubsystem()
{
}

void FWebServerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UGameInstanceSubsystem::Initialize(Collection);
	auto Router = FHttpServerModule::Get().GetHttpRouter(8842); 
	//Router->BindRoute("/board", );
}
