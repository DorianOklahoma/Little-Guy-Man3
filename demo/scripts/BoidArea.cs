using Godot;
using System;

public partial class BoidArea : Node2D
{
	[Export] public int NumberOfBoids = 5;
	[Export] public PackedScene Boid;
	

	public override void _Ready()
	{
		if (Boid == null)
		{
			GD.PrintErr("Boid not set.");
			return;
		}

		for (int i = 0; i < NumberOfBoids; i++)
		{
			SpawnBoid();
		}
	}

	private void SpawnBoid()
	{
		Boid boid = Boid.Instantiate<Boid>();
		AddChild(boid);
	}
}
