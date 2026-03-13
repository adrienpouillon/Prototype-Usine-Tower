using System.Collections.Generic;
using UnityEngine;


public class Machine : MonoBehaviour
{
    [Header("Configuration")]
    public Recipe currentRecipe;
    public float maxHealth = 10f;
    private float currentHealth = 10f;

    [Header("Inventaires")]
    public int maxStackSize = 50;
    // Dictionnaire pour gérer les entrées par type : <NomRessource, QuantitéActuelle>
    private Dictionary<string, int> inputInventory = new Dictionary<string, int>();
    public ResourceStack outputSlot;

    [Header("État de Production")]
    public float progressTimer = 0f;
    public bool isProcessing = false;

    void Start()
    {
        currentHealth = maxHealth;
        if (currentRecipe != null) InitializeMachine();
    }

    void InitializeMachine()
    {
        foreach (var req in currentRecipe.inputs)
        {
            inputInventory[req.type] = 0;
        }
        outputSlot = new ResourceStack { type = currentRecipe.output.type, amount = 0 };
    }

    // --- FONCTION DEMANDÉE : Tenter d'ajouter une ressource ---
    public bool TryAddResource(string resourceType, int amount)
    {
        if (currentRecipe != null)
        {
            //1.Vérifie si la ressource fait partie de la recette
            if (inputInventory.ContainsKey(resourceType))
            {
                // 2. Vérifie s'il y a de la place
                if (inputInventory[resourceType] + amount <= maxStackSize)
                {
                    inputInventory[resourceType] += amount;
                    return true;
                }
            }
        }
        else
        {
            Debug.LogWarning($"Machine {gameObject.name} n'a pas de recette assignée !");
            foreach (var inputType in currentRecipe.inputs)
            {
                if (inputType.type == resourceType)
                {
                    if (inputInventory.ContainsKey(resourceType) == false)
                        inputInventory[resourceType] = 0;

                    if (inputInventory[resourceType] + amount <= maxStackSize)
                    {
                        inputInventory[resourceType] += amount;
                        return true;
                    }
                }
            }
        }

        return false; // Refusé (mauvais type ou plein)
    }

    void Update()
    {
        if (currentRecipe == null) return;

        if (!isProcessing)
        {
            if (CanStartProduction())
            {
                StartProduction();
            }
        }
        else
        {
            UpdateProduction();
        }
    }

    bool CanStartProduction()
    {
        // Vérifie les ressources d'entrée
        foreach (var req in currentRecipe.inputs)
        {
            if (inputInventory[req.type] < req.amount) return false;
        }
        // Vérifie si la sortie n'est pas pleine
        if (outputSlot.amount + currentRecipe.output.amount > maxStackSize) return false;

        return true;
    }

    void StartProduction()
    {
        // Consomme les ressources
        foreach (var req in currentRecipe.inputs)
        {
            inputInventory[req.type] -= req.amount;
        }
        isProcessing = true;
        progressTimer = 0f;
    }

    void UpdateProduction()
    {
        progressTimer += Time.deltaTime;
        if (progressTimer >= currentRecipe.processingTime)
        {
            FinishProduction();
        }
    }

    void FinishProduction()
    {
        outputSlot.amount += currentRecipe.output.amount;
        isProcessing = false;
        //Debug.Log($"{gameObject.name} a produit : {currentRecipe.output.type}");
    }

    // --- SANTÉ ---
    public void TakeDamage(float damage)
    {
        currentHealth -= damage;
        if (currentHealth <= 0) Die();
    }

    void Die()
    {
        //Debug.Log("Machine détruite !");
        Destroy(gameObject);
    }
}